import { Component } from '@angular/core';
import { Lightbox } from 'ngx-lightbox';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'SECundumWebshopClient';

  private _albums: any = [];
  constructor(private _lightbox: Lightbox) {
    for (let i = 1; i <= 3; i++) {
      const src = './assets/caff_pictures/image' + i + '.png';
      const caption = 'Image ' + i + 'caption';
      const thumb = './assets/caff_pictures/image' + i + '.png';
      const album = { src: src, caption: caption, thumb: thumb};
      this._albums.push(album);
    }
  }

  open(index: number): void {
    this._lightbox.open(this._albums, index);
  }

  close(): void {
    this._lightbox.close();
  }
}
