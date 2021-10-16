const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const { CleanWebpackPlugin } = require("clean-webpack-plugin");

module.exports = {
  entry: "./lib/es6/src/Index.bs.js",
  mode: process.env.NODE_ENV === "production" ? "production" : "development",
  output: {
    path: path.join(__dirname, "build/"),
    filename: "[name].[chunkhash].js",
  },
  module: {
    rules: [{ test: /\.(png|jpg|svg)$/, use: "url-loader" }],
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./src/index.html",
    }),
    new CleanWebpackPlugin({
      watch: true,
    }),
  ],
};
