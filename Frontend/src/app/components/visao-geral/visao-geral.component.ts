import { Component, Input } from '@angular/core';
import { GaugeConsumoComponent } from '../gauge-consumo/gauge-consumo.component';

@Component({
  selector: 'app-visao-geral',
  imports: [GaugeConsumoComponent],
  templateUrl: './visao-geral.component.html',
  styleUrl: './visao-geral.component.scss'
})
export class VisaoGeralComponent {
  @Input() valor_kwh:any;
  @Input() total_kwh:any;
}
