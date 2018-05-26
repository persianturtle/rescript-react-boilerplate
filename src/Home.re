let component = ReasonReact.statelessComponent("Home");

let html = {|
  <h1>Home</h1>
  <p>This is a simple App Shell starter kit that you can use to get started building your <a target="_blank" href="https://developers.google.com/web/progressive-web-apps/">PWA</a> with the power of <a target="_blank" href="https://reasonml.github.io">Reason</a> and <a target="_blank" href="https://reasonml.github.io/reason-react/">ReasonReact</a>.</p>
  <p>Read the <a target="_blank" href="">tutorial for this App Shell starter kit on Medium</a>.</p>
  <p>Get the source on <a target="_blank" href="">Github</a>.</p>
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
|};

let make = _children => {
  ...component,
  render: _self =>
    <div className="Home" dangerouslySetInnerHTML={"__html": html} />
};