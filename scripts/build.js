import process from "child_process";
import { build } from "esbuild";
import svgrPlugin from "esbuild-plugin-svgr";
import generateServiceWorker from "./generateServiceWorker.js";
import injectScript from "./injectScript.js";

process.spawnSync("rm", ["-rf", "dist"], { stdio: "inherit", shell: true });
process.spawnSync("mkdir", ["dist"], { stdio: "inherit", shell: true });
process.spawnSync(
  "cp",
  ["-r", "src/index.html", "src/manifest.json", "img", "dist"],
  {
    stdio: "inherit",
    shell: true,
  }
);
process.spawnSync("mv", ["dist/img/favicon.ico", "dist"], {
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
      entryNames: "[name]-[hash]",
      outfile: "dist/app.js",
      minify: true,
      bundle: true,
      plugins: [svgrPlugin()],
    })
      .then(() => {
        injectScript();
        generateServiceWorker();
        console.timeEnd("\x1b[32m ⚡ esbuild\x1b[0m");
      })
      .catch((error) => {
        console.log(error);
        process.exit(1);
      });
  })();
}
