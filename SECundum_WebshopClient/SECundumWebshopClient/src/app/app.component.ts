import { Component } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Router } from '@angular/router';
import { Caff } from './caff';




@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'SECundumWebshopClient';
  public fileReaded: string;

  constructor(private http: HttpClient, private router: Router) { }

  uploadNewFile() {
    document.getElementById('upload-file').click();
  }

  addAttachment(fileInput: any) {
    this.fileReaded = fileInput.target.files[0];
    this.uploadFile()
  }

  uploadFile(): void {
    const baseUrl = "http://localhost:8080/caff/save";
    const token = sessionStorage.getItem('token');
    const headers = new HttpHeaders({
      'Auth': token
    })

    const formData = new FormData();
    formData.append("file", this.fileReaded);
    formData.append("reportProgress", "true");

    this.http.post(baseUrl, formData, { headers, responseType: 'json' }).subscribe(
      (response: Caff) => {
        this.reloadPage('/');
      }
    )

  }

  doLogout() {
    sessionStorage.setItem('token', '');
    document.getElementById('sign_in').style.visibility = "visible";
    document.getElementById('sign_up').style.visibility = "visible";
    document.getElementById('sign_out').style.visibility = "hidden";
  }

  reloadPage(url: String) {
    this.router.navigate([`${url}`])
      .then(() => {
        window.location.reload();
      });
  }

}
