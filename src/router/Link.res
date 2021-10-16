@scope("location") @val external pathname: string = "pathname"

@react.component
let make = (~href, ~children, ~isNavLink=false) => {
  <a
    href
    className={isNavLink && Js.String.startsWith(href, pathname) ? "active" : ""}
    onClick={event => {
      ReactEvent.Mouse.preventDefault(event)
      RescriptReactRouter.push(href)
    }}>
    children
  </a>
}
