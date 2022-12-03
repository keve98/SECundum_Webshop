import { ChangeDetectorRef, Component, Injectable, OnInit } from "@angular/core";
import { UserService } from "../user_service";
import { Router } from '@angular/router';
import { User } from "../user";
import { RouterModule, Routes } from '@angular/router';
import { HttpErrorResponse } from "@angular/common/http";
import { Token } from '../token';




@Injectable({
    providedIn: 'root'
})
@Component({ templateUrl: 'login.component.html' })
export class LoginComponent {

    username: string;
    password: string;


    routing: string = "";
    
    public user: User = new User;

    constructor(private userService: UserService, private router: Router, private route: RouterModule) {
        this.username = "";
        this.password = "";
    }



    async doLogin() {
        this.username = (<HTMLInputElement>document.getElementById('uname')).value;
        this.password = (<HTMLInputElement>document.getElementById('psw')).value;

        this.user.username = this.username;
        this.user.password = this.password;
        this.userService.login(this.user)
            .subscribe(
                (token: Token) => {
                    this.reloadPage("/");
                    sessionStorage.setItem('token', String(token.token));
                    alert(this.username + " signed in.")
                },
                (error) =>{
                    alert("Your login attempt was not successful. Please try again.")
                    this.reloadPage("/login");
                }
            );
    }

    reloadPage(url: String){
        this.router.navigate([`${url}`])
            .then(() => {
    window.location.reload();
  });
    }


   async doFunction() {
       await this.doLogin();
       this.router.navigate([`/`]);
    }

}