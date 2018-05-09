# Update

This is a new version that uses `bsb -init` in favor of `create-react-app`.
The previous router implementation was removed in favor of this instead:

[Reason React Router Example](https://gist.github.com/thangngoc89/c9162c0263df5427fe9a36fc7f94ac94)

Route transitions have been added using [React Transition Group](https://github.com/reactjs/react-transition-group) and an new Medium article will be coming soon regarding interop with existing ReactJS components.

TODO: add a service worker.

# Tutorial

[Tutorial on Medium.com](https://medium.com/@RRafatpanah/a-reasonml-tutorial-building-an-app-shell-dd7cc617d0c5)

# App Shell starter kit

<p>This is a simple App Shell starter kit that you can use to get started building your <a target="_blank" href="https://developers.google.com/web/progressive-web-apps/">PWA</a> with the power of <a target="_blank" href="https://reasonml.github.io">Reason</a> and <a target="_blank" href="https://reasonml.github.io/reason-react/">ReasonReact</a>.</p>

# Demo

<p>Check out the <a target="_blank" href="https://persianturtle.github.io/reason-app-shell-starter-kit/build/">demo here</a>.</p>
<img src="https://s3.amazonaws.com/persianturtle/demo.gif">
<p>Read the <a target="_blank" href="">tutorial for this App Shell starter kit on Medium</a>.</p>
<p>What's inside?</p>
<ul>
  <li>Initialized via <a target="_blank" href="https://github.com/reasonml-community/reason-scripts">Create React App (with reason-scripts)</a></li>
  <li>SPA routing with <a target="_blank" href="https://reasonml.github.io/reason-react/docs/en/router.html">ReasonReact's Router</a> and a helper <code>&lt;Link /&gt;</code> component</li>
  <li>Uses <code>(route, title)</code> tuples for routes</li>
  <li>A navigation that, when open, responds to touch&mdash;so you're free to use swiping gestures in your app</li>
  <li>One component per view</li>
</ul>
<p>In total, <code>app.re</code> is just around ~250 lines. Dive in, and change what you need!</p>
<h2>UI Inspiration</h2>
<ul>
  <li><a target="_blank" href="https://flowdash.co/">Flow Dashboard</a></li>
  <li><a target="_blank" href="https://material.angular.io/components/categories">Angular Material</a></li>
</ul>

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```
After you see the webpack compilation succeed (the `npm run webpack` step), open up `src/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version.

Read the [Medium article](https://medium.com/@RRafatpanah/a-reasonml-tutorial-building-an-app-shell-dd7cc617d0c5) for the full tutorial.
