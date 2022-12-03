import { Component, OnInit } from '@angular/core';
import { Comment } from '../comment';
import { CommentService } from '../comment_service';


@Component({
  selector: 'app-photo-details',
  templateUrl: './photo-details.component.html',
  styleUrls: ['./photo-details.component.css']
})
export class PhotoDetailsComponent implements OnInit {

  public imgName: string=sessionStorage.getItem('clickedImageName').replace('_', " ");
  public imgPath: string='./assets/caff_pictures/'+sessionStorage.getItem('clickedImageName')+'.png';
  public comments: Comment[] = [];
  private _albums: any = [];

  constructor(private commentService: CommentService) {
    this.commentService.getAllComment(sessionStorage.getItem('clickedImageName')).subscribe(data => {
      this.comments=data;
      this.showComments();
    })
  }

  showComments():void{
    for(const element of this.comments){
      const id = element.id;
      const caff_name = element.caff_name;
      const comment = element.comment;
      const comm = { id: id, caff_name: caff_name, comment: comment};
      this._albums.push(comm);
    }
  }

  ngOnInit(): void {
  }

}
