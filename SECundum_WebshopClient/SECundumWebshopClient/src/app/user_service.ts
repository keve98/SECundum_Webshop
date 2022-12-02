import {User} from './user';
import { ANALYZE_FOR_ENTRY_COMPONENTS, Injectable } from "@angular/core";
import { environment } from "src/environments/environment";
import {BehaviorSubject, Observable, throwError} from 'rxjs';
import {HttpClient, HttpHeaderResponse, HttpHeaders} from '@angular/common/http';
import { Router } from '@angular/router';

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

    public login(user: User):Observable<User>{
        var t = this.http.post<User>(`${this.apiServerUrl}/login`, user);
        return t;
             
     }

     public verify(code: String): Observable<User>{
        return this.http.get<User>(`${this.apiServerUrl}/verify/${code}`)
     }


    public saveUserData(user: User): Observable<any> {
        return this.http.post<any>(`${this.apiServerUrl}/save`, user);
      }
    

    public getAllUsers():Observable<User[]>{
        return this.http.get<User[]>(`${this.apiServerUrl}/admin`);
    }


    public getUserByUsername(username: string): Observable<User>{
        const t = this.http.get<User>(`${this.apiServerUrl}/user/${username}`)
        return t;
    }

    public logout(){
        this.http.get(`${this.apiServerUrl}/logout`);
    }

    async  isAdminOrUser():Promise<Observable<boolean>>{
        const t = await this.http.get<boolean>(`${this.apiServerUrl}/isAdmin`)
        return t;
    }

    searchUsernames(username: string): Observable<User[]>{
        const t = this.http.get<User[]>(`${this.apiServerUrl}/searchUsernames/${username}`);
        return t;
    }
}