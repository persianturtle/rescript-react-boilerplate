const process = require("child_process");
const { build } = require("esbuild");
const { sassPlugin } = require("esbuild-sass-plugin");

process.spawn("rm", ["-rf", "dist"], { stdio: "inherit", shell: true });
process.spawn("mkdir", ["dist"], { stdio: "inherit", shell: true });
process.spawn("cp", ["-r", "src/index.html", "img", "404.html", "dist"], {
  stdio: "inherit",
  shell: true,
});
process.spawn("npx", ["rescript"], { stdio: "inherit", shell: true });

(async () => {
  await build({
    entryPoints: ["lib/es6/src/Index.bs.js"],
    outfile: "dist/app.js",
    minify: true,
    bundle: true,
    loader: { ".svg": "file" },
    plugins: [sassPlugin()],
  }).catch(() => process.exit(1));
})();
