
const filesToCache = ["/app-AVKB5DUS.js","/favicon.ico","/img/demo.gif","/img/start.png","/"];
const currentCacheName = "rescript-react-boilerplate-3b22d2353c19a080ef67b225def691542f0f9d9fae3ce1bcc6385b5f044955b8";

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
        return await fetch(event.request);
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
    (async () =>
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
              .map((cacheName) => caches.delete(cacheName))
          )
        ))()
  );
});

self.addEventListener("message", (event) => {
  if (event.data.action === "skipWaiting") {
    self.skipWaiting();
  }
});
    