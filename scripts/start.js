const process = require("child_process");
const chokidar = require("chokidar");

build();
serve();

chokidar.watch("src/**/*", { ignoreInitial: true }).on("all", build);

function build() {
  process.spawn("node", ["scripts/build.js"], {
    stdio: "inherit",
    shell: true,
  });
}

function serve() {
  process.spawn(
    "npx",
    [
      "http-server",
      "-c-1",
      "--proxy",
      "http://localhost:8081?",
      "-p",
      "8081",
      "dist",
    ],
    { stdio: "inherit", shell: true }
  );
}