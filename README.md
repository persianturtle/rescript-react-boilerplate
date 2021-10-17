# Rescript React Boilerplate

An opinionated implementation of the following technologies:

- ReScript & React
- Simple routing using [ReScript's built in router](https://rescript-lang.org/docs/react/latest/router)
- Emotion for CSS-in-JS (or check our the [Sass branch](https://github.com/persianturtle/rescript-react-boilerplate/tree/sass))
- Quick and dirty route transitions via [ReactTransitionGroup](https://github.com/reactjs/react-transition-group)
- [http-server](https://github.com/http-party/http-server) for a quick and easy development server
- [esbuild](https://esbuild.github.io/) for fast bundling

# CSS Flavors

- [Emotion](https://github.com/persianturtle/rescript-react-boilerplate)
- [styled-ppx](https://github.com/persianturtle/rescript-react-boilerplate/tree/styled-ppx) (coming soon)
- [Sass](https://github.com/persianturtle/rescript-react-boilerplate/tree/sass)

## Getting Started

```sh
npm install
npm start
open http://localhost:8081
```

## Demo

![Demo](https://github.com/persianturtle/rescript-react-boilerplate/blob/master/img/demo.gif)

## Tutorial

(Video overview coming soon)

## Development Environment

Since we're using ReScript and esbuild, our build times are fast.

Because of this, we use [chokidar (a cross-platform file watcher)](https://github.com/paulmillr/chokidar) to watch for changes and then rebuild the `dist` directory on every change. The `dist` directory is the same whether in development or in production.

The build should work on macOS, Windows & Linux.

![Demo](https://github.com/persianturtle/rescript-react-boilerplate/blob/master/img/start.png)
