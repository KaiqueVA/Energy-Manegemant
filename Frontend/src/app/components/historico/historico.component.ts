import { NgForOf } from '@angular/common';
import { Component, Input } from '@angular/core';
import { MeasurementsService } from '../../services/measurements/measurements.service';

@Component({
  selector: 'app-historico',
  imports: [NgForOf],
  templateUrl: './historico.component.html',
  styleUrl: './historico.component.scss',
})
export class HistoricoComponent {

  dadosConsumo: any;
  @Input() tarifa:any;

  constructor(private measurementService: MeasurementsService) {}
  async ngOnInit() {
    this.dadosConsumo = (await this.measurementService.getSevenDays());
    console.log(this.dadosConsumo);
    this.dadosConsumo.map((e:any) => {
      e.valor_total = e.kwh * this.tarifa;
      e.data = new Date(e.data).toLocaleDateString();
    })

    this.dadosConsumo.reverse();

    this.dadosConsumo.shift();
  }
}
