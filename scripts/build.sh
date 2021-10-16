#!/bin/bash

rm -rf dist
mkdir dist
cp -r src/index.html src/img dist
npx rescript
npx esbuild lib/es6/src/Index.bs.js --bundle --loader:.svg=file --minify --outfile=dist/app.js
