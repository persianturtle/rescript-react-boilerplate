import process from "child_process";
import chokidar from "chokidar";

build();
serve();

chokidar.watch("src/**/*", { ignoreInitial: true }).on("all", build);

function build() {
  process.spawnSync("node", ["scripts/build.js"], {
    stdio: "inherit",
    shell: true,
  });
  console.log("\n");
}

function serve() {
  process.spawn(
    "npx",
    [
      "http-server",
      "-c-1",
      "--proxy",
      "http://localhost:8081?",
      "--port",
      "8081",
      "dist",
    ],
    { stdio: "inherit", shell: true }
  );
}
