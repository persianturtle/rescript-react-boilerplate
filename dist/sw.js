
const filesToCache = ["/app-CPIPWCRJ.js","/favicon.ico","/img/demo.gif","/img/icon/arrow.svg","/img/icon/chevron.svg","/img/icon/hamburger.svg","/img/icon/rescript_256x256.png","/img/icon/rescript_512x512.png","/img/rescript.svg","/img/start.png","/","/manifest.json"];
const currentCacheName = "rescript-react-boilerplate-baee58417d8693590a5b71f6fc13d9285f675bdba4221f2d8af75003d3e70714";

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
    