import { Component } from '@angular/core';
import { CustomInputComponent } from '../custom-input/custom-input.component';
import { FormsModule } from '@angular/forms';
import { User } from '../../classes/user';

@Component({
  selector: 'app-login-form',
  imports: [
    CustomInputComponent, FormsModule
  ],
  templateUrl: './login-form.component.html',
  styleUrl: './login-form.component.scss'
})
export class LoginFormComponent {
  user = new User("", "", "");
}
