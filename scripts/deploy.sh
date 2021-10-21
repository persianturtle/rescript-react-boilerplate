#!/bin/bash
# This script is used to deploy to GitHub pages

npm run build
echo 'rescript-react-boilerplate.persianturtle.com' > dist/CNAME
npx gh-pages -d dist
rm dist/CNAME
