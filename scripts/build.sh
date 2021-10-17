#!/bin/bash

rm -rf dist
mkdir dist
cp -r src/index.html img 404.html dist
npx rescript
npx esbuild lib/es6/src/Index.bs.js --bundle --loader:.svg=file --minify --outfile=dist/app.js
