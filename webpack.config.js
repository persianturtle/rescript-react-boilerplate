const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')
const WorkboxPlugin = require('workbox-webpack-plugin')
const WebpackPwaManifest = require('webpack-pwa-manifest')
const { CleanWebpackPlugin } = require('clean-webpack-plugin')

module.exports = {
  entry: './lib/es6/src/Index.bs.js',
  mode: process.env.NODE_ENV === 'production' ? 'production' : 'development',
  output: {
    path: path.join(__dirname, 'build/'),
    filename: '[name].[chunkhash].js'
  },
  module: {
    rules: [
      { test: /\.scss$/, use: ['style-loader', 'css-loader', 'sass-loader'] },
      { test: /\.(png|jpg|svg)$/, use: 'url-loader' }
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './src/index.html'
    }),
    new WorkboxPlugin.InjectManifest({
      swSrc: './src/sw.js'
    }),
    new WebpackPwaManifest({
      name: 'App Shell Boilerplate',
      short_name: 'AppShell',
      description: 'This is a description!',
      background_color: '#ffffff',
      icons: [
        {
          src: path.resolve('src/img/icon/icon.png'),
          size: '400x400'
        }
      ]
    }),
    new CleanWebpackPlugin({
      watch: true
    })
  ]
}
