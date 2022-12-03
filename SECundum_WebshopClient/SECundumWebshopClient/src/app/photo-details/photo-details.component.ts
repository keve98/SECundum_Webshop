import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CaffService } from '../caff_service';
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

  constructor(private http: HttpClient, private commentService: CommentService, private caffService: CaffService) {
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

downloadFile(): void{

  const baseUrl = "http://localhost:8080/caff/download?filename="+sessionStorage.getItem('clickedImageName');
  var filename = sessionStorage.getItem('clickedImageName')
  const token = sessionStorage.getItem('token');
 const headers = new HttpHeaders({
      'Content-Type':  'application/json',
      'Auth': token
    })

  this.http.get(baseUrl, {headers, responseType: 'blob' as 'json'}).subscribe(
      (response: any) =>{
          let dataType = response.type;
          let binaryData = [];
          binaryData.push(response);
          let downloadLink = document.createElement('a');
          downloadLink.href = window.URL.createObjectURL(new Blob(binaryData, {type: dataType}));
          if (filename)
              downloadLink.setAttribute('download', filename);
          document.body.appendChild(downloadLink);
          downloadLink.click();
      }
  )
}

  ngOnInit(): void {
  }

}
