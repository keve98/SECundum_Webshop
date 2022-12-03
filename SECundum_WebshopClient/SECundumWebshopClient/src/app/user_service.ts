import {User} from './user';
import { ANALYZE_FOR_ENTRY_COMPONENTS, Injectable } from "@angular/core";
import { environment } from "src/environments/environment";
import {BehaviorSubject, Observable, throwError} from 'rxjs';
import {HttpClient, HttpHeaderResponse, HttpHeaders} from '@angular/common/http';
import { Router } from '@angular/router';
import { Token } from './token';

@Injectable({
    providedIn: 'root'
})
export class UserService{
    private apiServerUrl=environment.apiBaseUrl;
    public user: Observable<User>;
    private userSubject: BehaviorSubject<User>;

    constructor(private http: HttpClient, private router: Router){
        this.userSubject = new BehaviorSubject<User>(JSON.parse(localStorage.getItem('user') || '{}'));
        this.user = this.userSubject.asObservable();
        console.log("userservice const");
    }

    createAuthorizationHeader(headers: Headers) {
        headers.append('Authorization', sessionStorage.getItem('token'));
      }

      //let headers = new Headers()
    //this.createAuthorizationHeader(headers)
    //return this.http.get<User>(`${this.apiServerUrl}/user/verify/${code}`{ //valszeg gethez nem lehet adni, esetleg guglizzunk utána
       // headers: headers
   // })

    public login(user: User):Observable<Token>{
        return this.http.post<Token>(`${this.apiServerUrl}/user/login`, user);
     }


    public saveUserData(user: User): Observable<User> {
        return this.http.post<User>(`${this.apiServerUrl}/user/save`, user);
      }
}
