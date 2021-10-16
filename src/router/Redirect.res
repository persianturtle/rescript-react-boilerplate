@react.component
let make = (~to_) => {
  React.useEffect(() => {
    RescriptReactRouter.replace(to_)

    None
  })

  React.null
}