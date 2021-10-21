import fs from "fs";

function injectStyles() {
  const fileName = fs
    .readdirSync("dist")
    .find((file) => file.startsWith("app") && file.endsWith(".css"));

  const file = fs
    .readFileSync("dist/index.html", "utf-8")
    .replace("</head>", `<link rel="stylesheet" href="${fileName}"></head>`);

  fs.writeFileSync("dist/index.html", file, "utf-8");
}

export default injectStyles;
