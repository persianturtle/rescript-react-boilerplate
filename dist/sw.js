
// Force the service worker to change if index.html changes
const indexHash = "05bfac3eae71c56833c5295a6c36a6b9e62b0b211806fdd0d85cb0ebbda679e9";
const filesToCache = ["/404.html","/app-AHOLRMYQ.js","/img/demo.gif","/img/start.png","/"];
const currentCacheName = "rescript-react-boilerplate-4d2c2e41d4097eb894662386b60839302685e34d6ad6127d3a556f6a3ead94cc";

self.addEventListener("install", (event) => {
  event.waitUntil(
    caches
      .open(currentCacheName)
      .then((cache) =>
        cache.addAll(["/404.html","/app-AHOLRMYQ.js","/img/demo.gif","/img/start.png","/"])
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
                cacheName.startsWith("rescript-react-boilerplate") &&
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
    