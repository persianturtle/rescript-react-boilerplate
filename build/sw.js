importScripts("precache-manifest.6b0c9c12b9b7cc2be6a868fbb20c832d.js", "https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

workbox.precaching.precacheAndRoute(self.__precacheManifest || []);
workbox.routing.registerNavigationRoute("/index.html");

