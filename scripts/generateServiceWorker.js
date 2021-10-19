const fs = require("fs");
const crypto = require("crypto");
const { name } = require("../package.json");

function generateServiceWorker() {
  const filesToCache = getFiles("dist");

  fs.writeFileSync(
    "dist/sw.js",
    `
const filesToCache = ${JSON.stringify(filesToCache)};
const currentCacheName = "${name}-${hash(
      filesToCache.join("") + fs.readFileSync("dist/index.html")
    )}";

self.addEventListener("install", (event) => {
  event.waitUntil(
    caches.open(currentCacheName).then((cache) => cache.addAll(filesToCache))
  );
});

self.addEventListener("fetch", (event) => {
  event.respondWith(
    (async () => {
      const cachedResponse = await caches.match(event.request);
      if (cachedResponse) {
        return cachedResponse;
      }

      try {
        return (await event.preloadResponse) ?? (await fetch(event.request));
      } catch (error) {
        if (event.request.mode === "navigate") {
          return caches.match("/");
        }

        throw error;
      }
    })()
  );
});

addEventListener("activate", (event) => {
  event.waitUntil(
    (async () => {
      if (self.registration.navigationPreload) {
        await self.registration.navigationPreload.enable();
      }

      return caches
        .keys()
        .then((cacheNames) =>
          Promise.all(
            cacheNames
              .filter(
                (cacheName) =>
                  cacheName.startsWith("rescript-react-boilerplate") &&
                  cacheName !== currentCacheName
              )
              .map((cacheName) => caches.delete(cacheName))
          )
        );
    })()
  );
});

self.addEventListener("message", (event) => {
  if (event.data.action === "skipWaiting") {
    self.skipWaiting();
  }
});
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
