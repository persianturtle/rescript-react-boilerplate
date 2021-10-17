#!/bin/bash

rm -rf dist
mkdir dist
cp src/index.html dist
npx rescript
npx esbuild lib/es6/src/Index.bs.js --bundle --loader:.svg=file --minify --outfile=dist/app.js

