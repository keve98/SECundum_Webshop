import { ANALYZE_FOR_ENTRY_COMPONENTS, Injectable } from "@angular/core";
import { environment } from "src/environments/environment";
import {BehaviorSubject, Observable, throwError} from 'rxjs';
import {HttpClient, HttpHeaderResponse, HttpHeaders} from '@angular/common/http';
import { Router } from '@angular/router';
import { Comment } from "./comment";


@Injectable({
    providedIn: 'root'
})
export class CommentService {
    private apiServerUrl=environment.apiBaseUrl;

    constructor(private http: HttpClient, private router: Router) {
    }

    createAuthorizationHeader(headers: Headers) {
        headers.append('Authorization', sessionStorage.getItem('token'));
    }

    public getAllComment(name: string):Observable<Comment[]> {
        return this.http.get<Comment[]>(`${this.apiServerUrl}/comment/getAll?caffName=${name}`);
    }

    public saveComment(comment: Comment):Observable<Comment> {
        return this.http.post<Comment>(`${this.apiServerUrl}/comment/save`, comment);
    }

    public deleteComment(id: string):Observable<string> {
        return this.http.delete<string>(`${this.apiServerUrl}/comment/delete?id=${id}`);
    }

}