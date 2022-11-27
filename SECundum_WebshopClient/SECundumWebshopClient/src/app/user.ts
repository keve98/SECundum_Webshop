export class User{
    username: string | undefined;
    password: string | undefined;
    email: string | undefined;
    token: string | undefined;

    constructor(){
        this.username = "";
        this.password = "";
        this.email = "";
        this.token = "";
    }
}