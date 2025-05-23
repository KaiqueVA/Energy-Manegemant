import { Component } from '@angular/core';
import { CustomInputComponent } from '../custom-input/custom-input.component';
import { User } from '../../classes/user';
import { ApiService } from '../../services/api/api.service';
import {FormsModule} from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-register-form',
  imports: [
    CustomInputComponent, FormsModule
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
