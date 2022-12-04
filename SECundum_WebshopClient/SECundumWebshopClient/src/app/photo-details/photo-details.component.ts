import { HttpClient, HttpErrorResponse, HttpHeaders, HttpResponse } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CaffService } from '../caff_service';
import { Comment } from '../comment';
import { CommentService } from '../comment_service';
import { Router } from '@angular/router';
import { catchError } from 'rxjs/operators';


@Component({
  selector: 'app-photo-details',
  templateUrl: './photo-details.component.html',
  styleUrls: ['./photo-details.component.css']
})
export class PhotoDetailsComponent implements OnInit {

  public imgName: string = sessionStorage.getItem('clickedImageName').replace('_', " ");
  public imgPath: string = './assets/caff_pictures/' + sessionStorage.getItem('clickedImageName') + '.png';
  public comments: Comment[] = [];
  private _albums: any = [];
  private newCommentString: string;
  private newCommentCaffname: string;
  private newComment: Comment;

  constructor(private http: HttpClient, private commentService: CommentService, private caffService: CaffService, private router: Router) {
    this.commentService.getAllComment(sessionStorage.getItem('clickedImageName')).subscribe(data => {
      this.comments = [];
      this._albums = [];
      this.comments = data;
      this.showComments();
    })
  }

  showComments(): void {
    for (const element of this.comments) {
      const id = element.id;
      const caff_name = element.caff_name;
      const comment = element.comment;
      const comm = { id: id, caff_name: caff_name, comment: comment };
      this._albums.push(comm);
    }
  }

  delComment(id): void {
    this.commentService.deleteComment(id).subscribe();
    this.reloadThisPage();
  }

  async createComment() {
    this.newCommentString = (<HTMLInputElement>document.getElementById('commentinput')).value;
    this.newCommentCaffname = sessionStorage.getItem('clickedImageName');
    this.newComment = {id: "", caff_name:this.newCommentCaffname, comment:this.newCommentString};
    this.commentService.saveComment(this.newComment).subscribe();
    this.commentService.getAllComment(sessionStorage.getItem('clickedImageName')).subscribe(data => {
      this.comments = [];
      this._albums = [];
      this.comments = data;
      this.showComments();
    });
    (<HTMLInputElement>document.getElementById('commentinput')).value = "";
    this.reloadThisPage();
  }

  reloadThisPage(): void {
    this.reloadPage('/photo-details');
  }


  downloadFile(): void {

    const baseUrl = "http://localhost:8080/caff/download?filename=" + sessionStorage.getItem('clickedImageName');
    var filename = sessionStorage.getItem('clickedImageName')
    const token = sessionStorage.getItem('token');
    const headers = new HttpHeaders({
      'Content-Type': 'application/json',
      'Auth': token
    })

    this.http.get(baseUrl, { headers, responseType: 'blob' as 'json' }).subscribe(
      (response: any) => {
        let fileName = filename + '.caff';
        let dataType = response.type;
        let binaryData = [];
        binaryData.push(response);
        var link = document.createElement('a');
        link.href = window.URL.createObjectURL(new Blob(binaryData, { type: dataType }));
        link.download = fileName;
        link.click();
      }
    )
  }

  ngOnInit(): void {
  }

  reloadPage(url: String) {
    this.router.navigate([`${url}`])
      .then(() => {
        window.location.reload();
      });
  }

  async createNewComment() {
    await this.createComment();
    this.router.navigate([`/photo-details`]);
  }

}
