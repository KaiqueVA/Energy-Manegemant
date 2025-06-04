import { Component, Input } from '@angular/core';
import { GaugeConsumoComponent } from '../gauge-consumo/gauge-consumo.component';
import { MeasurementsService } from '../../services/measurements/measurements.service';

@Component({
  selector: 'app-visao-geral',
  imports: [GaugeConsumoComponent],
  templateUrl: './visao-geral.component.html',
  styleUrl: './visao-geral.component.scss'
})
export class VisaoGeralComponent {
  @Input() tarifa:any;
  consumo:any = 1;
  valor_total = 0;

  constructor(private measurementService: MeasurementsService){

  }

  async ngOnInit(){
    // this.consumo = (await this.measurementService.getToday()).consumoTotal;
    this.valor_total = this.tarifa*this.consumo;
    console.log(this.consumo);
  }
}
