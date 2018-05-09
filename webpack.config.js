const path = require("path");
const exec = require("child_process").exec;

module.exports = {
  entry: "./lib/es6/src/Index.bs.js",
  mode: process.env.NODE_ENV === "production" ? "production" : "development",
  output: {
    path: path.join(__dirname, "build/"),
    publicPath: path.join(__dirname, "build/"),
    filename: "index.js"
  },
  module: {
    rules: [
      { test: /\.scss$/, use: ["style-loader", "css-loader", "sass-loader"] },
      { test: /\.(png|jpg|svg)$/, use: "url-loader" }
    ]
  },
  plugins: [
    {
      apply: compiler => {
        compiler.hooks.afterEmit.tap("AfterEmitPlugin", compilation => {
          exec("cp -r ./src/index.html ./build", (err, stdout, stderr) => {
            if (stdout) process.stdout.write(stdout);
            if (stderr) process.stderr.write(stderr);
          });
        });
      }
    }
  ]
};
