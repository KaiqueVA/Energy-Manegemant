import { Injectable } from '@angular/core';
import { ApiService } from '../api/api.service';

@Injectable({
  providedIn: 'root',
})
export class MeasurementsService {
  constructor(private apiService: ApiService) {}

  // Converte Watts para kWh
  calcularConsumoTotalKwh(medidas: any[]): number {
    if (medidas.length < 2) return 0;

    let consumoTotal = 0;

    for (let i = 1; i < medidas.length; i++) {
      const anterior = medidas[i - 1];
      const atual = medidas[i];

      const pAtivaMedia = (anterior.p_ativa + atual.p_ativa) / 2;
      const tempoHoras =
        (new Date(atual.createdAt).getTime() -
          new Date(anterior.createdAt).getTime()) /
        1000 /
        3600;

      consumoTotal += pAtivaMedia * tempoHoras;
    }

    return Number(consumoTotal.toFixed(4));
  }

  // Agrupa os dados por dia (retorna um objeto com data como chave)
  agruparPorDia(medidas: any[]): { [data: string]: any[] } {
    return medidas.reduce((acc, medida) => {
      const data = new Date(medida.createdAt).toISOString().split('T')[0];
      if (!acc[data]) acc[data] = [];
      acc[data].push(medida);
      return acc;
    }, {} as { [data: string]: any[] });
  }

  // Gera um array com consumo por dia
  calcularConsumoDiario(
    medidas: any[]
  ): { data: string; consumoKwh: number }[] {
    const agrupado = this.agruparPorDia(medidas);
    return Object.entries(agrupado).map(([data, medidasDoDia]) => ({
      data,
      consumoKwh: this.calcularConsumoTotalKwh(medidasDoDia),
    }));
  }

  async getToday() {
    const today = await this.apiService.fetchMeasurements('today');
    const consumoTotal = this.calcularConsumoTotalKwh(today);
    return {
      medidas: today,
      consumoTotal,
    };
  }

  async getWeek() {
    const week = await this.apiService.fetchMeasurements('this-week');
    const consumoPorDia = this.calcularConsumoDiario(week);
    const consumoTotal = consumoPorDia.reduce(
      (acc, d) => acc + d.consumoKwh,
      0
    );
    return {
      medidas: week,
      consumoPorDia,
      consumoTotal: Number(consumoTotal.toFixed(4)),
    };
  }

  async getSevenDays() {
    const sevenDays = await this.apiService.fetchMeasurements('last-7-days');
    const consumoPorDia = this.calcularConsumoDiario(sevenDays);
    const consumoTotal = consumoPorDia.reduce(
      (acc, d) => acc + d.consumoKwh,
      0
    );
    return {
      medidas: sevenDays,
      consumoPorDia,
      consumoTotal: Number(consumoTotal.toFixed(4)),
    };
  }
}
