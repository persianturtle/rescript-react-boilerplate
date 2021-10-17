const process = require("child_process");
const { build } = require("esbuild");
const { sassPlugin } = require("esbuild-sass-plugin");

process.spawnSync("rm", ["-rf", "dist"], { stdio: "inherit", shell: true });
process.spawnSync("mkdir", ["dist"], { stdio: "inherit", shell: true });
process.spawnSync("cp", ["-r", "src/index.html", "img", "404.html", "dist"], {
  stdio: "inherit",
  shell: true,
});

console.time("\x1b[32m ✨ ReScript\x1b[0m");
const { status } = process.spawnSync("npx", ["rescript"], {
  stdio: "inherit",
  shell: true,
});

// Continue only if ReScript compiles successfully
if (status === 0) {
  console.timeEnd("\x1b[32m ✨ ReScript\x1b[0m");

  (async () => {
    console.time("\x1b[32m ⚡ esbuild\x1b[0m");
    await build({
      entryPoints: ["lib/es6/src/Index.bs.js"],
      outfile: "dist/app.js",
      minify: true,
      bundle: true,
      loader: { ".svg": "file" },
      plugins: [sassPlugin()],
    })
      .then((a) => {
        console.timeEnd("\x1b[32m ⚡ esbuild\x1b[0m");
      })
      .catch(() => process.exit(1));
  })();
}
