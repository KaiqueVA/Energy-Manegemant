import { NgClass, NgIf } from '@angular/common';
import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'app-switch-tomada',
  imports: [NgIf, NgClass],
  templateUrl: './switch-tomada.component.html',
  styleUrl: './switch-tomada.component.scss',
})
export class SwitchTomadaComponent {
  @Input() ativo = false;

  toggle(): void {
    this.ativo = !this.ativo;
  }
}
