import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { User } from '../../classes/user';
import { ApiService } from '../../services/api/api.service';
import { Router, RouterEvent } from '@angular/router';

@Component({
  selector: 'app-login-form',
  imports: [FormsModule],
  templateUrl: './login-form.component.html',
  styleUrl: './login-form.component.scss',
})
export class LoginFormComponent {
  user = new User("", "", "");
  
    constructor(private apiService: ApiService, private router: Router){
    }
  
    async onSubmit(){
      await this.apiService.fetchLogin(this.user)
      .then(result => {
        console.log(result);
        if (result) {
          this.router.navigate(['/dashboard']);
        }
      })
    }
}
