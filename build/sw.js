importScripts("precache-manifest.9d92c417be162d3ecd38aa9bbb2df120.js", "https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

workbox.precaching.precacheAndRoute(self.__precacheManifest || []);
workbox.routing.registerNavigationRoute("/index.html");

