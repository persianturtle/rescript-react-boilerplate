const process = require("child_process");
const { build } = require("esbuild");
const svgrPlugin = require("esbuild-plugin-svgr");

process.spawnSync("rm", ["-rf", "dist"], { stdio: "inherit", shell: true });
process.spawnSync("mkdir", ["dist"], { stdio: "inherit", shell: true });
process.spawnSync("cp", ["-r", "src/index.html", "img", "404.html", "dist"], {
  stdio: "inherit",
  shell: true,
});

console.time("\u001b[1;32m ✨ ReScript");
const { status } = process.spawnSync("npx", ["rescript"], {
  stdio: "inherit",
  shell: true,
});

// Continue only if ReScript compiles successfully
if (status === 0) {
  console.timeEnd("\u001b[1;32m ✨ ReScript");

  (async () => {
    console.time("\u001b[1;32m ⚡ esbuild");
    await build({
      entryPoints: ["lib/es6/src/Index.bs.js"],
      outfile: "dist/app.js",
      minify: true,
      bundle: true,
      plugins: [svgrPlugin()],
    })
      .then((a) => {
        console.timeEnd("\u001b[1;32m ⚡ esbuild");
      })
      .catch(() => process.exit(1));
  })();
}
