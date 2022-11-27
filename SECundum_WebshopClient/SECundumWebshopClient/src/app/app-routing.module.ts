import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
//import { AdminComponent } from './admin';
//import { HomeComponent } from './home';
import { LoginComponent } from './login';
//import { PlayerComponent } from './player';
import { RegistrationComponent } from './registration';
//import { VerifyNotSuccessfulComponent } from './verify-not-successful/verify-not-successful.component';
//import { VerifySuccessfulComponent } from './verify-successful/verify-successful.component';
//import { VerifyComponent } from './verify/verify.component';
import { AuthGuard } from './auth.guard';       // path után ezt baszd oda amit nem láthat aki nincs bejelentkezve: ,canActivate: [AuthGuard]



const routes: Routes = [
  {path:'login',component:LoginComponent},
  //{path: 'admin', component: AdminComponent},
  //{path: 'home', component: HomeComponent},
  {path: 'registration', component: RegistrationComponent}
  //{path: 'player', component: PlayerComponent},
  //{path: 'verify/:code', component: VerifyComponent},
  //{path: 'verifySuccessful', component: VerifySuccessfulComponent},
  //{path: 'verifyNotSuccessful', component: VerifyNotSuccessfulComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }