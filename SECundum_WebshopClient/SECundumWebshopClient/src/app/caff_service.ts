import { ANALYZE_FOR_ENTRY_COMPONENTS, Injectable } from "@angular/core";
import { environment } from "src/environments/environment";
import { Caff } from "./caff";
import {BehaviorSubject, Observable, throwError} from 'rxjs';
import {HttpClient, HttpHeaderResponse, HttpHeaders} from '@angular/common/http';
import { Router } from '@angular/router';



@Injectable({
    providedIn: 'root'
})
export class CaffService {
    private apiServerUrl=environment.apiBaseUrl;
    private caffSubject: BehaviorSubject<Caff>;

    constructor(private http: HttpClient, private router: Router) {
        this.caffSubject = new BehaviorSubject<Caff>(JSON.parse(localStorage.getItem('caff') || '{}'));
    }

    createAuthorizationHeader(headers: Headers) {
        headers.append('Authorization', sessionStorage.getItem('token'));
    }

    //let headers = new Headers()
    //this.createAuthorizationHeader(headers)
    //return this.http.get<User>(`${this.apiServerUrl}/user/verify/${code}`{ //valszeg gethez nem lehet adni, esetleg guglizzunk utána
       // headers: headers
   // })

    public getAllCaff():Observable<Caff[]> {
        return this.http.get<Caff[]>(`${this.apiServerUrl}/caff/getAll`);
    }

    public getCaffByName(name: string):Observable<Caff> {
        return this.http.get<Caff>(`${this.apiServerUrl}/caff/get/${name}`);
    }

    public downloadCaff(name: string):Observable<any> {
        var token = sessionStorage.getItem('token')
            const httpOptions = {
                headers: new HttpHeaders({
                  'Content-Type':  'application/json',
                  'Auth': token
                })
              };
        return this.http.get<any>(`${this.apiServerUrl}/caff/download?name=${name}`, httpOptions);
    }

    public uploadCaff(file: File):Observable<Caff> {
        return this.http.post<Caff>(`${this.apiServerUrl}/caff/save`, file);
    }

}