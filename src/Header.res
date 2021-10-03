%%raw(`import styled, {css} from 'styled-components'`)

@obj
external scProps: (~children: React.element, unit) => {"children": React.element} = ""

let sc = %raw(`
    styled.header\`
      display: flex;
      align-items: center;
      height: 60px;
      background-color: dodgerblue;
      color: white;
      box-shadow: 0 4px 5px 0 rgba(15, 74, 133, 0.14),
        0 2px 9px 1px rgba(15, 74, 133, 0.12),
        0 4px 2px -2px rgba(15, 74, 133, 0.2);

      > a {
        display: flex;
        align-items: center;
        width: 32px;
        height: 100%;
        padding: 0 10px;
        cursor: pointer;

        > img {
          width: 100%;
          height: 100%;
        }
      }

      > h1 {
        font-size: 26px;
        line-height: 26px;
        margin-left: 10px;
      }
    \`
  `)
