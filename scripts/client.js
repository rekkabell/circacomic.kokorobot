'use strict'

function Client () {
  this.el = document.getElementById('client')
  this._controls = document.createElement('div')
  this._controls.id = 'controls'
  this._viewer = document.createElement('div')
  this._viewer.id = 'viewer'
  this.index = 0
  this.pages = 7

  this.install = (host) => {
    this.el.appendChild(this._controls)
    this.el.appendChild(this._viewer)
    this._controls.innerHTML = `
    <a href='#' onclick="client.home()">home</a>
    <a href='#' onclick="client.back()">< back</a>
    <a href='#' id='location'></a>
    <a href='#' onclick="client.next()">next ></a>
    <a href='#' onclick="client.last()">last</a>`

    document.onkeydown = (e) => {
      if (e.key === 'ArrowRight') { e.preventDefault(); this.next() } else if (e.key === 'ArrowLeft') { e.preventDefault(); this.back() }
    }
  }

  this.start = () => {
    this.home()
  }

  this.go = (page) => {
    this.index = page > this.pages ? this.pages : page < 0 ? 0 : page

    let html = ''

    for (let i = 0; i < this.pages; i++) {
      html += `<span class='${i < this.index ? 'seen' : 'unseen'}'>|</span>`
    }
    document.getElementById('location').innerHTML = html

    this._viewer.innerHTML = `<img src='media/content/ch1.p${this.index + 1}.jpg'/>`
  }

  // Controls

  this.home = () => {
    this.go(0)
  }

  this.next = () => {
    this.go(this.index + 1)
  }

  this.back = () => {
    this.go(this.index - 1)
  }

  this.last = () => {
    this.go(this.pages)
  }
}
