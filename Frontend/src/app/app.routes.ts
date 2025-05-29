import { Routes } from '@angular/router';
import { LoginPageComponent } from './pages/login-page/login-page.component';
import { DashboardComponent } from './pages/dashboard/dashboard.component';
import { RegisterPageComponent } from './pages/register-page/register-page.component';
import { authGuard } from './guards/auth.guard';

export const routes: Routes = [
  { path: '', component: LoginPageComponent },
  { path: 'dashboard', component: DashboardComponent, canActivate: [authGuard] },
  { path: 'register', component: RegisterPageComponent },
];