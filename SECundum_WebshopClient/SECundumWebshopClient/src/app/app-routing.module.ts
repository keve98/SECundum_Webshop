import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { LoginComponent } from './login';
import { RegistrationComponent } from './registration';
import { AuthGuard } from './auth.guard';       // path után ezt baszd oda amit nem láthat aki nincs bejelentkezve: ,canActivate: [AuthGuard]
import { PhotoGalleryComponent } from './photo-gallery/photo-gallery.component';


const routes: Routes = [
  {path:'login',component:LoginComponent},
  {path: 'registration', component: RegistrationComponent},
  {path: 'photo-gallery', component: PhotoGalleryComponent},
  {path: '', redirectTo: 'photo-gallery', pathMatch: 'full'}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }