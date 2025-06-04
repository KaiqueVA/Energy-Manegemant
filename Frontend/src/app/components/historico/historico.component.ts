import { NgForOf } from '@angular/common';
import { Component } from '@angular/core';
import { MeasurementsService } from '../../services/measurements/measurements.service';

@Component({
  selector: 'app-historico',
  imports: [NgForOf],
  templateUrl: './historico.component.html',
  styleUrl: './historico.component.scss',
})
export class HistoricoComponent {

  dadosConsumo: any;

  constructor(private measurementService: MeasurementsService) {}
  async ngOnInit() {
    this.dadosConsumo = (await this.measurementService.getSevenDays()).consumoPorDia;
    console.log(this.dadosConsumo);
  }
}
