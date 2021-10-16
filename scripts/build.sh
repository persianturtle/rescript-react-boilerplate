#!/bin/bash

rm -rf dist
mkdir dist
cp src/index.html dist
npx rescript
npx esbuild lib/es6/src/Index.bs.js --bundle --minify --outfile=dist/app.js