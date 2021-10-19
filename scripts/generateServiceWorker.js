const fs = require("fs");
const crypto = require("crypto");
const { name } = require("../package.json");

function generateServiceWorker() {
  const filesToCache = getFiles("dist");

  fs.writeFileSync(
    "dist/sw.js",
    `
// Force the service worker to change if index.html changes
const indexHash = "${hash(fs.readFileSync("dist/index.html"))}";
const filesToCache = ${JSON.stringify(filesToCache)};
const currentCacheName = "${name}-${hash(filesToCache.join(""))}";

self.addEventListener("install", (event) => {
  event.waitUntil(
    caches
      .open(currentCacheName)
      .then((cache) =>
        cache.addAll(${JSON.stringify(filesToCache)})
      )
  );
});

self.addEventListener("fetch", (event) => {
  if (
    filesToCache
      .map((file) => self.location.protocol + "//" + self.location.host + file)
      .includes(event.request.url)
  ) {
    return event.respondWith(caches.match(event.request));
  }

  return fetch(event.request)
});

self.addEventListener("activate", async (event) => {
  event.waitUntil(
    caches
      .keys()
      .then((cacheNames) =>
        Promise.all(
          cacheNames
            .filter(
              (cacheName) =>
                cacheName.startsWith("${name}") &&
                cacheName !== currentCacheName
            )
            .map(cacheName => caches.delete(cacheName))
        )
      )
  );
});

self.addEventListener("message", event => {
  if (event.data.action === "skipWaiting") {
    self.skipWaiting()
  }
})
    `
  );
}

function getFiles(dir) {
  return fs.readdirSync(dir).flatMap((item) => {
    const path = `${dir}/${item}`;
    if (fs.statSync(path).isDirectory()) {
      return getFiles(path);
    }

    return path.replace(/dist|index.html/g, "");
  });
}

function hash(string) {
  return crypto.createHash("sha256").update(string, "utf8").digest("hex");
}

module.exports = generateServiceWorker;
