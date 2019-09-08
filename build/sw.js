importScripts("precache-manifest.b903b0a744241e84ff3f2129497e1381.js", "https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

workbox.precaching.precacheAndRoute(self.__precacheManifest || []);
workbox.routing.registerNavigationRoute("/index.html");

