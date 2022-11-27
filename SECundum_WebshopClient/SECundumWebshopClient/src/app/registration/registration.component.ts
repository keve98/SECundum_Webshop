import { Component } from "@angular/core";
import { Router } from "@angular/router";
import { User } from "../user";
import { UserService } from "../user_service";

@Component({
    selector: 'app-registration',
    templateUrl: 'registration.component.html'
})
export class RegistrationComponent{
    

    public user= new User();

    constructor(private userService: UserService, private router : Router){ }

    public save(): void{
        this.user.username = (<HTMLInputElement>document.getElementById('username')).value;
        this.user.password = (<HTMLInputElement>document.getElementById('psw')).value;
        this.user.email = (<HTMLInputElement>document.getElementById('email')).value;
        this.user.token = (<HTMLInputElement>document.getElementById('token')).value;

        this.userService.saveUserData(this.user).subscribe(
            (data : User) => {
                alert("Registration successful. We sent an email with your verification link. Please click on it to complete the registration.");
                this.router.navigate([`/login`]);
            },
            (error) => {
                alert("Something went wrong, try again.");
                this.router.navigate([`/registration`]);
            }
        );

        this.router.navigate([`/`]);

    }
}