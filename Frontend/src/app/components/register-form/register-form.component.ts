import { Component } from '@angular/core';
import { User } from '../../classes/user';
import { ApiService } from '../../services/api/api.service';
import {FormsModule} from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-register-form',
  imports: [
    FormsModule
  ],
  templateUrl: './register-form.component.html',
  styleUrl: './register-form.component.scss'
})
export class RegisterFormComponent {

  user = new User("", "", "");

  constructor(private apiService: ApiService, private router: Router){
  }

  async onSubmit(){
    await this.apiService.fetchRegister(this.user)
    .then(result => {
      console.log(result);
      if (result) {
        this.router.navigate(['/dashboard']);
      }
    })
  }
}
