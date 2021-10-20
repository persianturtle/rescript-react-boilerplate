import fs from "fs";

function injectScript() {
  const fileName = fs
    .readdirSync("dist")
    .find((file) => file.startsWith("app") && file.endsWith(".js"));

  const file = fs
    .readFileSync("dist/index.html", "utf-8")
    .replace("</body>", `<script src="${fileName}"></script></body>`);

  fs.writeFileSync("dist/index.html", file, "utf-8");
}

export default injectScript;
