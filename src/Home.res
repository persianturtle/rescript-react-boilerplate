let html = `
  <h1>Rescript React Boilerplate</h1>
  <p>An opinionated implementation of the following technologies:</p>
  <ul>
    <li>ReScript & React</li>
    <li>Simple routing using <a target="_blank" href="https://rescript-lang.org/docs/react/latest/router">ReScript's built in router</a></li>
    <li>Emotion for CSS-in-JS (or check our the <a target="_blank" href="https://github.com/persianturtle/rescript-react-boilerplate/tree/sass">Sass branch</a>)</li>
    <li>Quick and dirty route transitions via <a target="_blank" href="https://github.com/reactjs/react-transition-group">ReactTransitionGroup</a></li>
    <li><a target="_blank" href="https://github.com/http-party/http-server">http-server</a> for a quick and easy development server</li>
    <li><a target="_blank" href="https://esbuild.github.io/">esbuild</a> for fast bundling</li>
  </ul>
  <h2>Getting Started</h2>
  <pre><code class="sh language-sh">npm install
npm start
open http://localhost:8081
  </code></pre>
  <h2>Demo</h2>
  <img src="/img/demo.gif" alt="Demo" />
  <h2>Tutorial</h2>
  <p>(Video overview coming soon)</p>
  <h2>Development Environment</h2>
  <p>Since we're using ReScript and esbuild, our build times are fast.</p>
  <p>Because of this, we use <a target="_blank" href="https://github.com/paulmillr/chokidar">chokidar (a cross-platform file watcher)</a> to watch for changes and then rebuild the <code>dist</code> directory on every change. The <code>dist</code> directory is the same whether in development or in production.</p>
  <p>The build should work on macOS, Windows & Linux.</p>
  <img src="/img/start.png" alt="Example npm start output" />
`

@react.component
let make = () =>
  <div
    className={Emotion.css(`
      padding: 30px;

      img {
        max-width: 700px;

        @media (max-width: 767px) {
          max-width: 100%;
        }
      }
    `)}
    dangerouslySetInnerHTML={"__html": html}
  />
