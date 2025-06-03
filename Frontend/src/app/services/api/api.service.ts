import { Injectable } from '@angular/core';
import { User } from '../../classes/user';

@Injectable({
  providedIn: 'root',
})
export class ApiService {
  api_url = 'http://localhost:8080/';
  api_token = '123';

  constructor() {}

  async fetchRegister(user: User) {
    return fetch(this.api_url + 'auth/register', {
      method: 'POST',
      mode: 'cors',
      headers: {
        'Content-Type': 'application/json',
        Authorization: 'Bearer ' + this.api_token,
      },
      body: JSON.stringify(user),
    })
      .then((response) => response.json())
      .then((result) => {
        sessionStorage.setItem('token', result.token);
        sessionStorage.setItem('name', result.name);
        return true;
      })
      .catch(error => console.error("Erro ao registar!", error));
  }

  async fetchLogin(user: User) {
    return fetch(this.api_url + 'auth/login', {
      method: 'POST',
      mode: 'cors',
      headers: {
        'Content-Type': 'application/json',
        Authorization: 'Bearer ' + this.api_token,
      },
      body: JSON.stringify(user),
    })
      .then((response) => response.json())
      .then((result) => {
        console.log(result);
        sessionStorage.setItem('token', result.token);
        sessionStorage.setItem('name', result.name);
        return true;
      })
      .catch(error => console.error("Erro ao fazer login!", error));
  }

  async fetchMeasurements() {
    return fetch(this.api_url + 'measurements', {
      headers: {
        'Content-Type': 'application/json',
        Authorization: 'Bearer ' + sessionStorage.getItem('token'),
      },
    })
      .then((response) => response.json())
      .then((result) => {
        return result;
      });
  }
}
