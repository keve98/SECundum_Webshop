import { Component, OnInit } from '@angular/core';
import { Lightbox } from 'ngx-lightbox';
import { CaffService } from "../caff_service";
import { Caff } from '../caff';

@Component({
  selector: 'app-photo-gallery',
  templateUrl: './photo-gallery.component.html',
  styleUrls: ['./photo-gallery.component.css']
})
export class PhotoGalleryComponent implements OnInit {

  public caffs: Caff[] = [];
  private _albums: any = [];
  constructor(private _lightbox: Lightbox, private caffService: CaffService) {
    this.caffService.getAllCaff().subscribe(data=> {
      this.caffs = data;
    })
    this.caffs.forEach(element => {
      const src = './assets/caff_pictures/' + element.content.replace(' ', '_') + '.png';
      const caption = element.content.replace(' ', '_') + 'caption';
      const thumb = './assets/caff_pictures/image' + element.content.replace(' ', '_') + '.png';
      const album = { src: src, caption: caption, thumb: thumb};
      this._albums.push(album);
    });
  }

  open(index: number): void {
    this._lightbox.open(this._albums, index);
  }

  close(): void {
    this._lightbox.close();
  }

  ngOnInit(): void {
    
  }


}
